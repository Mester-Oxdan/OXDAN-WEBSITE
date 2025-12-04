async function confirm_email(e) {
    e.preventDefault();
    const r = {
        code: document.getElementById("code").value,
        csrf_token: window.CSRF_TOKEN
    };
    
    fetch("/api/confirm_email_new_password.php", {
        method: "POST",
        headers: {"Content-Type": "application/json"},
        body: JSON.stringify(r)
    }).then((e => e.json())).then((e => {
        document.getElementById("response").innerHTML = "";
        if ("success" === e.status) {
            Alert.success("Success! Code verified successfully.", "Success", {displayDuration: 4e3});
            window.location.href = "/change_password";
        } else if ("blocked" === e.status) {
            startBlockedCountdown(e.remaining);
            Alert.error(e.message, "Blocked", {displayDuration: 4e3});
        } else if ("error" === e.status) {
            switch(e.message) {
                case "wrong code.":
                case "Error wrong code.":
                    Alert.error("Error! Wrong Code.", "Error", {displayDuration: 4e3});
                    break;
                case "No data received":
                    Alert.error("Error! No Data Received.", "Error", {displayDuration: 4e3});
                    break;
                case "Valid email required":
                    Alert.error("Error! Valid Email Required.", "Error", {displayDuration: 4e3});
                    break;
                case "Code required":
                    Alert.error("Error! Code Required.", "Error", {displayDuration: 4e3});
                    break;
                case "No verification code found. Please request a new one.":
                    Alert.error("Error! Code Expired. Request New One.", "Error", {displayDuration: 4e3});
                    break;
                case "Error opening file.":
                    Alert.error("Error! Connecting To Database.", "Error", {displayDuration: 4e3});
                    break;
                case "Error writing to file.":
                    Alert.error("Error! Writing To Database.", "Error", {displayDuration: 4e3});
                    break;
                case "Too many attempts for confirm_email_new_password_1":
                    Alert.error("Error! Too Many Attempts. Wait 1 minute before trying again.", "Error", {displayDuration: 4e3});
                    break;
                case "Too many attempts for confirm_email_new_password_2":
                    Alert.error("Error! Too Many Attempts. Wait 5 minutes before trying again.", "Error", {displayDuration: 4e3});
                    break;
                case "Too many attempts for confirm_email_new_password_3":
                    Alert.error("Error! Too Many Attempts. Wait 10 minutes before trying again.", "Error", {displayDuration: 4e3});
                    break;
                case "Too many attempts for confirm_email_new_password_4":
                    Alert.error("Error! Too Many Attempts. Wait 15 minutes before trying again.", "Error", {displayDuration: 4e3});
                    break;
                default:
                    Alert.error("Error! " + e.message, "Error", {displayDuration: 6e3});
            }
        }
    })).catch((e => {
        Alert.error("Error! Something Went Wrong. Message: " + e, "Error", {displayDuration: 4e3});
    }));
}

let blockedInterval = null;
function startBlockedCountdown(e) {
    const r = document.getElementById("code"), t = document.getElementById("confirm-btn");
    r.disabled = !0, t.disabled = !0, blockedInterval = setInterval((() => {
        e--, r.placeholder = `Blocked. Try again in ${e}s`, e <= 0 && (clearInterval(blockedInterval), r.disabled = !1, t.disabled = !1, r.placeholder = "Enter your code");
    }), 1e3);
}

let countdownSeconds = 60, countdownInterval = null;
function startCountdown() {
    const e = document.getElementById("countdown"), r = document.getElementById("resend-timer"), t = document.getElementById("resend-link");
    e && r && t && (t.classList.add("disabled", "hidden"), t.style.pointerEvents = "none", t.style.opacity = "0.5", r.classList.remove("hidden"), countdownSeconds = 60, e.textContent = countdownSeconds, countdownInterval && clearInterval(countdownInterval), countdownInterval = setInterval((() => {
        countdownSeconds--, e.textContent = countdownSeconds, countdownSeconds <= 0 && (clearInterval(countdownInterval), r.classList.add("hidden"), t.classList.remove("hidden", "disabled"), t.style.pointerEvents = "auto", t.style.opacity = "1");
    }), 1e3));
}

function resendEmail() {
    const e = document.getElementById("resend-link");
    
    e.classList.add("disabled");
    e.style.pointerEvents = "none";
    e.style.opacity = "0.5";
    
    fetch("/api/resend_email.php", {
        method: "POST",
        headers: {"Content-Type": "application/json"},
        body: JSON.stringify({ type: 'password_reset', csrf_token: window.CSRF_TOKEN })
    }).then((response => response.json())).then((data => {
        if ("success" === data.status) {
            Alert.success("Success! New verification code sent!", "Success", {displayDuration: 4e3});
            startCountdown();
        } else {
            Alert.error("Error! " + (data.message || "Failed to resend code."), "Error", {displayDuration: 4e3});
            e.classList.remove("disabled");
            e.style.pointerEvents = "auto";
            e.style.opacity = "1";
        }
    })).catch((error => {
        Alert.error("Error! Something went wrong.", "Error", {displayDuration: 4e3});
        e.classList.remove("disabled");
        e.style.pointerEvents = "auto";
        e.style.opacity = "1";
    }));
}

document.addEventListener("DOMContentLoaded", (function() {
    startCountdown();
    const e = document.getElementById("resend-link");
    e && e.addEventListener("click", (function() {
        e.classList.contains("disabled") || e.classList.contains("hidden") ? Alert.info("Please Wait Until Timer Finishes.", "Info", {displayDuration: 2500}) : resendEmail();
    }));
}));
