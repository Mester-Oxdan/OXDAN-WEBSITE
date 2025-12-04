# OXDAN-WEBSITE
Oxdan Production Website.

A modern website for Oxdan Production Company built with HTML/CSS, JavaScript and PHP.

## 🚀 Quick Start

```bash
cd OXDAN-DRAGON-WEBSITE
php -S localhost:8002 router.php
```
Visit: http://localhost:8002

## 📁 Project Structure

```
OXDAN-DRAGON-WEBSITE/
├── index.html              # Homepage (split-view: Console | Shop)
├── router.php              # URL routing
├── app.db                  # SQLite database
│
├── pages/                  # User-facing pages
│   ├── login.php           # User login
│   ├── register.php        # User registration
│   ├── faq.html            # FAQ page
│   └── lists.html          # Community lists
│
├── api/                    # Backend PHP (27 files)
│   ├── database.php        # SQLite setup
│   ├── login.php           # Authentication
│   ├── register.php        # Registration
│   ├── get_products.php    # Shop products
│   ├── fetch_comments.php  # Comments
│   ├── submit_rating.php   # Ratings
│   └── ...
│
└── files/                  # Static assets
    ├── css/                # Stylesheets
    ├── js/                 # Scripts
    ├── resources/          # Images, fonts, music
    └── catalogs_html/      # Product pages
```

## ⚠️ Requirements

- PHP 7.4 or higher
- Composer (PHP dependency manager)

```bash
composer require aws/aws-sdk-php vlucas/phpdotenv google/apiclient
```

Vendor folder should be in `files/resources/vendor/`.

## 🔧 Environment Variables (.env)

```
AWS_REGION_ACCESS_KEY=
AWS_ID_ACCESS_KEY=
AWS_SECRET_ACCESS_KEY=
RECAPTCHA_SECRET_ACCESS_KEY=
GOOGLE_CLIENT_ID_ACCESS_KEY=
GOOGLE_CLIENT_SECRET_ACCESS_KEY=
```

## ❌ TODO / Missing

- [ ] **Composer dependencies** - Need `composer install` for AWS SES, Google OAuth
- [ ] **About page** - To implement
- [ ] **3D Printing Shop page** - Browse products
- [ ] **Promo codes page** - Enter promo codes

---

## 📱 Social Media

- **YouTube:** [@Oxdan_Praduction](https://www.youtube.com/@Oxdan_Praduction)
- **TikTok:** [@oxdan_praduction](https://www.tiktok.com/@oxdan_praduction)
- **Instagram:** [@oxdanpraduction](https://instagram.com/oxdanpraduction)
- **Facebook:** [@Mariia Sierova](https://www.facebook.com/profile.php?id=100087125340188)
- **GitHub:** [@Mester-Oxdan](https://github.com/Mester-Oxdan)
- **Reddit:** [u/detektive-void](https://www.reddit.com/u/detektive-void)

## 💼 Freelance

- **Kwork:** [@jecob](https://kwork.com/user/jecob)
- **Fiverr:** [@jecob_567](https://www.fiverr.com/jecob_567)
- **Upwork:** [Profile](https://www.upwork.com/freelancers/~01e296384cd379e73e)

## 🛒 Shops

- **TikTok Shop:** [@oxdan_praduction_shop](https://www.tiktok.com/@oxdan_praduction_shop)
- **Shopify:** [933791-66.myshopify.com](https://933791-66.myshopify.com/)
- **eBay:** [oxdan_praduction](https://www.ebay.com/usr/oxdan_praduction)

## 💰 Support / Donations

- **Cash App:** $BoHladii (4403 9352 3234 1307)
- **Buy Me A Coffee:** [buymeacoffee.com/oxdan](https://www.buymeacoffee.com/oxdan)

## 🌐 Website

**https://oxdan.com**

---

## 📜 About Dragon Console

!REMEMBER! Author is not responsible for your actions with this console. Created for learning programming and testing security.

**Features:**
- 9 command categories: MAINS, HACKER_STUFFS, PICTURES, ACCOUNTS, SERIOUS, GAMES, OWNS, PRANKS, ELSES
- Available in C/C++ and Python versions
- Made for Windows

**Found a bug?** Email: bogerter4521de@gmail.com  
Your name could be on the leaders board in the lists section!

Started as a coding learning project in 2023, became the author's first major program.

---

Thanks! 🙏😊

© 2024 Oxdan Production
