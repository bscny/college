const client = require('node-fetch');

const BASE_URL = 'http://localhost:3000/hogRider';

const testGetSuccess = async () => {
    let resp = await client(`${BASE_URL}/tom`, { method: 'GET' });
    let data = await resp.json();
    console.log("GET 'tom':\n", data);
}

const testGetFailed = async () => {
    resp = await client(`${BASE_URL}/mary`, { method: 'GET' });
    data = await resp.json();
    console.log("GET 'mary':\n", data);
}

const runAllTests = async () => {
    await testGetSuccess();
    console.log("\n");

    await testGetFailed();
    console.log("\n");
};

runAllTests();
