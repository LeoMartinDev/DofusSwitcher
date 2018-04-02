import DofusWindowsEvent from "./src/renderer/components/DofusWindowsEvent";

const dofusEvents = new DofusWindowsEvent();

dofusEvents.on('login', process => {
  process.setToForegroundAsync(function(error, success) {
    if (error) console.error(error);
    else
  })
});

process.on('uncaughtException', function (error) {
  console.error('uncaughtException : ', error)
});