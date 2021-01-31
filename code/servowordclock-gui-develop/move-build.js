const fs = require('fs');
const fse = require('fs-extra');
const resolve = require('path').resolve

const buildFolder = resolve('./build/');
const targetFolder = resolve('../ServoWordClockESP8266/data');

console.log(`moving from "${buildFolder}" to "${targetFolder}"`);

const rules = [
    { pattern: /^bundle\..*\.js$/, target: "bundle.js", replace: true },
    { pattern: /^bundle\..*\.css$/, target: "bundle.css", replace: true },
    { pattern: /^polyfills\..*\.js$/, target: "polyfills.js", replace: true },
    { pattern: /^favicon\.ico$/, target: "favicon.ico" },
    { pattern: /^manifest\.json$/, target: "manifest.json" },
    { pattern: /^index\.html$/, target: "index.html" }
]
const replacements = [];
const replaceFiles = [];
const replaceRules = [{ pattern: /^index\.html$/ }]

if (fs.existsSync(targetFolder)) {
    fs.rmdirSync(targetFolder, { recursive: true });
}
fs.mkdirSync(targetFolder, { recursive: true });

fs.readdir(buildFolder, { withFileTypes: true }, (err, files) => {
    files.forEach(dirent => {
        if (dirent.isDirectory()) {
            fse.copySync(buildFolder + "\\" + dirent.name, targetFolder + "\\" + dirent.name);
        } else {
            rules.forEach(rule => {
                if (rule.pattern.test(dirent.name)) {
                    if (rule.replace) {
                        const replacer = new RegExp(dirent.name, 'g')
                        replacements.push({ replace: replacer, with: rule.target });
                    }
                    fs.copyFileSync(buildFolder + "\\" + dirent.name, targetFolder + "\\" + rule.target);
                }
            })
            replaceRules.forEach(rep => {
                if (rep.pattern.test(dirent.name)) {
                    console.log(dirent.name)
                    replaceFiles.push(dirent.name);
                }
            });
        }
    });
    replaceContent();
});

function replaceContent(){
    replaceFiles.forEach(name => {
        const file = targetFolder + "\\" + name;
        console.log(file);
        let data = fs.readFileSync(file, 'utf8');
        replacements.forEach(replacement => {
            data = data.replace(replacement.replace, replacement.with)
        })
        fs.writeFileSync(file, data, 'utf8');
    });
    console.log("=> done");
}