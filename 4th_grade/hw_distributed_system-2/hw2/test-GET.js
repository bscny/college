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

const printAll = async () => {
    const resp = await client(`${BASE_URL}`, {
        method: 'GET'
    });

    const data = await resp.json();
    console.log("All Hog Riders:\n", data);
}

const runAllTests = async () => {
    await testGetSuccess();
    await printAll();
    console.log("\n");

    await testGetFailed();
    await printAll();
    console.log("\n");

    await testPost();
    await printAll();
    console.log("\n");

    await testPut();
    await printAll();
    console.log("\n");
};

runAllTests();
