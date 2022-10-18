let port;
let IP;

if (chrome && chrome.runtime) {
  port = chrome.runtime.connect();
}

document.addEventListener("DOMContentLoaded", function () {
  // Init
  init();

  // Actions

  document.getElementById("control-up").addEventListener("click", () => {
    fetch(`${getAppUrlAction()}stop`);

    /**
     * @description Lets wait few ms before switching control!
     */
    setTimeout(() => {
      fetch(`${getAppUrlAction()}up`);
    }, 200);
  });

  document.getElementById("control-down").addEventListener("click", () => {
    fetch(`${getAppUrlAction()}stop`);

    /**
     * @description Lets wait few ms before switching control!
     */
    setTimeout(() => {
      fetch(`${getAppUrlAction()}down`);
    }, 200);
  });

  document.getElementById("control-stop").addEventListener("click", () => {
    fetch(`${getAppUrlAction()}stop`);
  });

  document.getElementById("openSettingsBtn").addEventListener("click", () => {
    document.getElementById("settings").style.display = "block";
    document.getElementById("controls").style.display = "none";
  });

  document.getElementById("closeSettingsBtn").addEventListener("click", () => {
    document.getElementById("settings").style.display = "none";
    document.getElementById("controls").style.display = "block";
  });

  document.getElementById("inputIPBtn").addEventListener("keyup", (event) => {
    const inputIPValue = event.target.value;
    console.log(inputIPValue);
    localStorage.setItem("inputIPValue", inputIPValue);
  });
});

/**
 * @description Init method to init device IP in form :)
 */
function init() {
  IP = localStorage.getItem("inputIPValue");
  document.getElementById("inputIPBtn").value = IP;
}

/**
 * @description Init method to init device IP in form :)
 */
function getAppUrlAction() {
  if (!IP || IP === "") {
    alert("Missing IP information");
    return;
  }

  return `http://${IP}/action?value=`;
}
