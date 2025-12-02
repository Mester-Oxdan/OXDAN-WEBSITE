function change_password(e) {
    e.preventDefault();
    
    const email = localStorage.getItem('reset_email');
    if (!email) {
        Alert.error("Error! Session expired. Please start password reset again.", "Error", {displayDuration: 4000});
        return;
    }
    
    var r = {
        email: email,
        newpassword: document.getElementById("password").value,
        deviceInfo: {
            userAgent: navigator.userAgent,
            screenResolution: window.screen.width + "x" + window.screen.height
        },
        csrf_token: window.CSRF_TOKEN,
        recaptcha_response: recaptchaResponse
    };
    
    var o = grecaptcha.getResponse(widgetId1);
    if (null === o || "" === o) {
        Alert.error("Error! Please Confirm You Are Not A Robot.", "Error", {displayDuration: 4e3});
        return;
    }
    
    fetch("../files/php/change_password_2.php", {
        method: "POST",
        headers: {"Content-Type": "application/json"},
        body: JSON.stringify(r)
    }).then((e => e.json())).then((e => {
        const r = document.getElementById("response");
        if (r.innerHTML = "", "success" === e.status) {
            var o = document.createElement("h2"), 
                s = document.createElement("h2"), 
                n = new Audio("../resources/musics/undertale.mp3");
            
            function t(e) {
                localStorage.removeItem('reset_email');
                localStorage.removeItem('reset_username');
                window.location.href = {skip_login: "/skip_login"}[e];
            }
            
            Alert.success("Success! Password Changed successfully.", "Success", {displayDuration: 4e3});
            o.textContent = "!Password Changed Successfully!";
            s.textContent = "Press any key to continue";
            r.appendChild(o);
            r.appendChild(s);
            n.play();
            document.addEventListener("keydown", (function(e) {
                t("skip_login");
            }));
            document.addEventListener("mousedown", (function(e) {
                t("skip_login");
            }));
        } else {
            "error" === e.status && (
                "Same password." === e.message ? 
                Alert.error("Error! You Enter The Same Password.", "Error", {displayDuration: 4e3}) :
                "No data received" === e.message ? 
                Alert.error("Error! No data received by server.", "Error", {displayDuration: 4e3}) :
                "User not found." === e.message ? 
                Alert.error("Error! User not found.", "Error", {displayDuration: 4e3}) :
                "User account has invalid password data." === e.message ? 
                Alert.error("Error! Account has invalid password data.", "Error", {displayDuration: 4e3}) :
                "Email or password missing." === e.message ? 
                Alert.error("Error! Email or password missing.", "Error", {displayDuration: 4e3}) :
                "Invalid request method." === e.message ? 
                Alert.error("Error! PHP Request Failed.", "Error", {displayDuration: 4e3}) :
                Alert.error("Error! " + e.message, "Error", {displayDuration: 4e3})
            );
        }
    })).catch((e => {
        Alert.error("Error! Something Went Wrong. Error Message: ", e, "Error", {displayDuration: 4e3});
    }));
}
