const client = require('node-fetch');

const BASE_URL = 'http://localhost:3000/hogRider';

const testPut = async () => {
    const tomUpdatePayload = { name: "tom", age: 99, attack: 0, defense: 0 };
    resp = await client(`${BASE_URL}/tom`, {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(tomUpdatePayload)
    });
    data = await resp.json();
    console.log("PUT 'tom':\n", data);
}

const runAllTests = async () => {
    await testPut();
    console.log("\n");
};

runAllTests();
