document.addEventListener('DOMContentLoaded', loadFaqs);

function loadFaqs(query = '') {
    fetch(`../files/php/search.php?query=${encodeURIComponent(query)}`)
        .then(response => response.json())
        .then(data => {
            const faqList = document.getElementById('faqList');
            faqList.innerHTML = '';
            data.forEach((item, index) => {
                const faqId = `faq-${index}`;

                const checkbox = document.createElement('input');
                checkbox.type = 'checkbox';
                checkbox.id = faqId;

                const label = document.createElement('label');
                label.setAttribute('for', faqId);

                const question = document.createElement('p');
                question.classList.add('faq-heading');
                question.textContent = item.question;

                const arrow = document.createElement('div');
                arrow.classList.add('faq-arrow');

                const answer = document.createElement('p');
                answer.classList.add('faq-text');
                answer.textContent = item.answer;

                label.appendChild(question);
                label.appendChild(arrow);
                label.appendChild(answer);

                faqList.appendChild(checkbox);
                faqList.appendChild(label);
            });
        });
}

function searchFaqs() {
    const query = document.getElementById('searchBar').value;
    loadFaqs(query);
}
