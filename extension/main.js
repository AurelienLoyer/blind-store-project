/**
 * @description
 * potential url http://192.168.1.27/action?value=stop
 */

var port = chrome.runtime.connect();
var appUrlAction = 'http://192.168.1.27/action?value='

document.addEventListener("DOMContentLoaded", function () {
  document.getElementById("control-up").addEventListener("click", () => {
    fetch(`${appUrlAction}up`);
  });

  document.getElementById("control-down").addEventListener("click", () => {
    fetch(`${appUrlAction}down`);
  });

  document.getElementById("control-stop").addEventListener("click", () => {
    fetch(`${appUrlAction}stop`);
  });
});
