const puppeteer = require('puppeteer');

(async () => {
    const browser = await puppeteer.launch();
    const page = await browser.newPage();

    try {
        await page.goto('https://example.com', { waitUntil: 'networkidle2' });
        
        // Wait for a specific element to be available
        await page.waitForSelector('#someElement', { timeout: 5000 });

        // Perform actions on the element
        const result = await page.evaluate(() => {
            // Your code here
        });

        console.log(result);
    } catch (error) {
        console.error('Error occurred:', error);
    } finally {
        await browser.close();
    }
})();
