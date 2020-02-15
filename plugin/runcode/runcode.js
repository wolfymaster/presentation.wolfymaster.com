const RunCode = window.RunCode || function () {

    let options = Reveal.getConfig().runcode || {};

    let defaultOptions = {
        text: "Run"
    };

    const defaults = function (options, defaultOptions) {
        for (let i in defaultOptions) {
            if (!options.hasOwnProperty(i)) {
                options[i] = defaultOptions[i];
            }
        }
    };

    const buildStructure = function (element) {

        let runbutton = document.createElement("button");
        runbutton.textContent = options.text;
        runbutton.style.right = "100px";
        runbutton.className = "runcode";
        runbutton.setAttribute('data-language', element.childNodes[0].getAttribute('data-language'));

        element.parentNode.prepend(runbutton);
    };

    const makeRequest = async function (code, language) {
        console.log(encodeURI(code), language);
        let url = "http://api.paiza.io/runners/create?";
        url += "source_code="+encodeURIComponent(code);
        url += "&language="+language;
        url += "&api_key=guest";

        console.log(url);

        // make post request
        const resJson = await fetch(url, {
            method: 'POST',
            mode: 'cors',
            body: ''
        });

        const { id, error } = await resJson.json();

        if (error) {
            console.error("Failed to POST code with error: " + error);
        }

        // poll status
        await new Promise( (resolve, reject) => {
            (async function pollStatus() {
                // get result
                let stat = await fetch("http://api.paiza.io/runners/get_status?api_key=guest&id=" + id);
                let { status } = await stat.json();
                if (status === "completed") {
                    return resolve();
                }

                setTimeout(pollStatus, 2000);
            })();
        });

        // display result
        const compiledResultJson = await fetch("http://api.paiza.io/runners/get_details?api_key=guest&id=" + id);
        return await compiledResultJson.json();
    };

    const init = function () {

        defaults(options, defaultOptions);

        let codeblocks = document.querySelectorAll("pre");

        codeblocks.forEach(function (codeblock) {
            buildStructure(codeblock);
        });

        let clipboard = new ClipboardJS(".runcode", {
            target: function (trigger) {
                return trigger.nextElementSibling.nextElementSibling;
            }
        });

        clipboard.on("success", function (e) {
            console.log(e.trigger);
            e.clearSelection();
            let copiedText = e.text;

            let result = makeRequest(copiedText, e.trigger.getAttribute('data-language'));

            result.then( (compiledResult) => {
                let { stdout, stderr } = compiledResult;
                alert(stdout);
            });
        });
    };

    return {
        init: init
    };
}();

Reveal.registerPlugin("runcode", RunCode);