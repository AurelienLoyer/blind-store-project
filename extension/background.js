chrome.runtime.onConnect.addListener(function (externalPort) {
  console.log("extension open !");

  externalPort.onDisconnect.addListener(function () {
    var ignoreError = chrome.runtime.lastError;
    console.log("onDisconnect triggered");

    // @todo use value from localstorage here!
    fetch("http://192.168.1.49/action?value=stop").catch(console.error);
  });
});
