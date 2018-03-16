import {getProcessesByNameAsync} from 'windows-process';
import {EventEmitter} from 'events';
import * as _ from 'lodash';

export default class DofusWindowsEvent extends EventEmitter {

  constructor() {
    super();
    this.connectedProcesses = [];
    this.loop.call(this);
  }

  loop() {
    setTimeout(() => {
      getProcessesByNameAsync("Dofus")
        .then(processes => {
          this.connectedProcesses.forEach(process => {
            let index = processes.findIndex(value => value.id === process.id);

            if (index < 0) {
              if (this.connectedProcesses.splice(index, 1).length > 0) {
                this.emit('close', process);
              }
            }
          });
          processes.forEach(process => {
            let index = this.connectedProcesses.findIndex(value => value.id === process.id);

            if (process.mainWindowTitle === "Dofus") {
              if (index > -1) {
                if (this.connectedProcesses.splice(index, 1).length > 0) {
                  this.emit('logout', process);
                }
              } else {
                this.emit('new-window', process);
              }
            }
            else if (process.mainWindowTitle !== "" && process.mainWindowTitle !== "Dofus") {
              if (index < 0) {
                this.connectedProcesses.push(process);
                this.emit('login', process);
              }
            }
            else {
              if (this.connectedProcesses.splice(index, 1).length > 0) {
                this.emit('logout', process);
              }
            }
          });
          this.loop.call(this);
        });
    }, 200);
  };

}