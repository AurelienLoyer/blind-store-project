chrome.runtime.onConnect.addListener(function (externalPort) {
  console.log("extension open !");

  externalPort.onDisconnect.addListener(function () {
    var ignoreError = chrome.runtime.lastError;
    console.log("onDisconnect triggered");
    fetch("http://192.168.1.27/action?value=stop").catch(console.error);
  });
});
