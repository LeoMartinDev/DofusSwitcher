const {GetProcessesByName, GetCurrentProcess} = require('./build/Release/addon.node');

// `Hello` function returns a string, so we have to console.log it!
console.log(GetProcessesByName());
console.log(GetCurrentProcess());