// NEED MS VS VERSION 2007 !!!!!!!!!!!!!!!!!!!

const addon = require('./build/Release/addon');

const {app, globalShortcut, BrowserWindow} = require('electron')

function createWindow () {
    // Create the browser window.
    //win = new BrowserWindow({width: 800, height: 600})

    // and load the index.html of the app.
    let dofusAccounts = addon.getProcessesByName("Dofus")
    let i = 0;
    globalShortcut.register('CommandOrControl+X', () => {
        dofusAccounts[i].setToForeground();
        i++;
        if (i >= dofusAccounts.length) i = 0;
    })
/*    win.loadURL(url.format({
        pathname: path.join(__dirname, 'index.html'),
        protocol: 'file:',
        slashes: true
    }))*/
}

app.on('ready', createWindow)
