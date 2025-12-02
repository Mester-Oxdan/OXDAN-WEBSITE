function change_password(event) {
    event.preventDefault();
    var currentpasswordInput = document.getElementById('current_password');
    var newpasswordInput = document.getElementById('password');
    var password = currentpasswordInput.value;
    var newpassword = newpasswordInput.value;
    var recaptchaResponse = grecaptcha.getResponse(widgetId1);

    var deviceInfo = {
        userAgent: navigator.userAgent,
        screenResolution: window.screen.width + "x" + window.screen.height
    };

    var loginData = {
        password: password,
        newpassword: newpassword,
        deviceInfo: deviceInfo,
        csrf_token: window.CSRF_TOKEN,
        recaptcha_response: recaptchaResponse
    };
    
    if (recaptchaResponse === null || recaptchaResponse === "") {
        Alert.error('Error! Please Confirm You Are Not A Robot.', 'Error', { displayDuration: 4000 });
    } else {
        fetch('../files/php/change_password.php', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(loginData)
        })
        .then(response => response.json())
        .then(result => {
            const responseDiv = document.getElementById('response');
            responseDiv.innerHTML = '';
            if (result.status === 'success') {
                var h2 = document.createElement('h2');
                var paragraph = document.createElement('h2');
                var audio = new Audio('../files/resources/musics/undertale.mp3');
                Alert.success('Success! Password Changed successfully.', 'Success', { displayDuration: 4000 });
                h2.textContent = '!Password Changed Successfully!';
                paragraph.textContent = 'Press any key to continue';
                responseDiv.appendChild(h2);
                responseDiv.appendChild(paragraph);
                audio.play();
                function redirectTo(page) {
                    const routes = {
                        'skip_login': '/skip_login'
                    };
                    window.location.href = routes[page];
                }
                document.addEventListener('keydown', function(event) {
                    redirectTo('skip_login');
                });
                document.addEventListener('mousedown', function(event) {
                    redirectTo('skip_login');
                });    
            } else if (result.status === 'error') {
                if (result.message === 'Current password is incorrect.') {
                    Alert.error('Error! Current Password Is Incorrect.', 'Error', { displayDuration: 4000 });
                } else if (result.message === 'User not found.') {
                    Alert.error('Error! User Not Found.', 'Error', { displayDuration: 4000 });
                } else if (result.message === 'User account has invalid password data.') {
                    Alert.error('Error! Account Has Invalid Password Data.', 'Error', { displayDuration: 4000 });
                } else if (result.message === 'All fields are required.') {
                    Alert.error('Error! All Fields Are Required.', 'Error', { displayDuration: 4000 });
                } else if (result.message === 'No data received') {
                    Alert.error('Error! No Data Received By Server.', 'Error', { displayDuration: 4000 });
                } else if (result.message === 'Same password.') {
                    Alert.error('Error! You Enter The Same Password.', 'Error', { displayDuration: 4000 });
                } else if (result.message === 'Invalid request method.') {
                    Alert.error('Error! PHP Request Failed.', 'Error', { displayDuration: 4000 });
                } else {
                    Alert.error('Error! ' + result.message, 'Error', { displayDuration: 4000 });
                }
            }
        })
        .catch(error => {
            Alert.error('Error! Something Went Wrong. Error Message: ' + error, 'Error', { displayDuration: 4000 });
        });
    }
}
