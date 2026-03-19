const client = require('node-fetch');

const BASE_URL = 'http://localhost:3000/hogRider';

const testPost = async () => {
    const maryPayload = { name: "mary", age: 17, attack: 99, defense: 99 };
    resp = await client(`${BASE_URL}`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(maryPayload)
    });
    data = await resp.json();
    console.log("POST 'mary':\n", data);
}

const runAllTests = async () => {
    await testPost();
    console.log("\n");
};

runAllTests();
