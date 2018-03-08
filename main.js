const addon = require('bindings')('addon');
let dofusAccounts = addon.getProcessesByName("Dofus");
console.log(dofusAccounts[0])
/*
const {app, globalShortcut, BrowserWindow} = require('electron')

function createWindow () {
    // Create the browser window.
    //win = new BrowserWindow({width: 800, height: 600})

    // and load the index.html of the app.
    let dofusAccounts = addon.getProcessesByName("Dofus");
    globalShortcut.register('CommandOrControl+X', () => {
        console.log('CommandOrControl+X is pressed')
    })
/!*    win.loadURL(url.format({
        pathname: path.join(__dirname, 'index.html'),
        protocol: 'file:',
        slashes: true
    }))*!/
}

app.on('ready', createWindow)*/
