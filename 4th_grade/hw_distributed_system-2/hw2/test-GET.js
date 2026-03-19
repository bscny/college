const client = require('node-fetch');

const BASE_URL = 'http://localhost:3000/hogRider';

const printAll = async () => {
    const resp = await client(`${BASE_URL}`, {
        method: 'GET'
    });

    const data = await resp.json();
    console.log("All Hog Riders:\n", data);
}

const runAllTests = async () => {
    await printAll();
    console.log("\n");
};

runAllTests();
