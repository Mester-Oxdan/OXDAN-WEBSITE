document.getElementById('upload-input').addEventListener('change', function(event) {
    const file = event.target.files[0];
    const formData = new FormData();
    formData.append('file', file);
    const imageFileType = file.name.split('.').pop().toLowerCase();
    const allowedFormats = ["jpg", "jpeg", "png", "gif"];
    const maxSize = 5000000;

    if (!allowedFormats.includes(imageFileType)) {
        Alert.error('Error! Only JPG, JPEG, PNG, GIF Files Are Allowed.', 'Error', { displayDuration: 4000 });
        return;
    }

    if (file.size > maxSize) {
        Alert.error('Error! Your File Is Too Large. No More Than 5MB.', 'Error', { displayDuration: 4000 });
        return;
    }

    fetch('/api/avatar_picture_storage/upload.php', {
        method: 'POST',
        body: formData
    })
    .then(response => response.json())
    .then(data => {
        if (data.status === 'success') {
            Alert.success('Success! Image Uploaded Successfully.', 'Success', { displayDuration: 4000 });
            document.getElementById('profile-pic').src = '/api/avatar_picture_storage/uploads/' + data.file;
        } else {
            if (data.error) {
                Alert.error('Error! ' + data.error, 'Error', { displayDuration: 4000 });
            } else {
                Alert.error('Error! Uploading File Failed.', 'Error', { displayDuration: 4000 });
            }
        }
    })
    .catch(error => {
        Alert.error('Error! Something Went Wrong. Error Message: ' + error.message, 'Error', { displayDuration: 4000 });
    });
});

window.onload = function() {
    fetch('/api/avatar_picture_storage/get_uploaded_image.php')
    .then(response => response.json())
    .then(data => {
        if (data.status === 'success' && data.file) {
            document.getElementById('profile-pic').src = '/api/avatar_picture_storage/' + data.file;
        } else {
            Alert.error('Error! Connecting To Database.', 'Error', { displayDuration: 4000 });
        }
    })
    .catch(error => {
        Alert.error('Error! Something Went Wrong. Error Message: ' + error.message, 'Error', { displayDuration: 4000 });
    });
};
