const server = require('fastify')();

let john = {
    name: "john",
    age: 18,
    attack: 100,
    defense: 100
};

let tom = {
    name: "tom",
    age: 19,
    attack: 105,
    defense: 90
};

let hogRiders = [john, tom];

server.get('/hogRider', function (req, res) {
    return hogRiders;
});

server.get('/hogRider/:name', function (req, res) {
    const name = req.params.name;
    
    const rider = hogRiders.find(r => r.name === name);
    
    if (rider) {
        return rider;
    } else {
        res.code(404);
        return { "error": "not found" };
    }
});

server.post('/hogRider', function (req, res) {
    const newRider = req.body;
    
    hogRiders.push(newRider);
    
    res.code(201);
    return { count: hogRiders.length };
});

server.put('/hogRider/:name', function (req, res) {
    const name = req.params.name;
    const index = hogRiders.findIndex(r => r.name === name);
    
    if (index !== -1) {
        hogRiders[index] = { ...hogRiders[index], ...req.body };
        return hogRiders[index];
    } else {
        res.code(404);
        return { "error": "not found" };
    }
});


server.listen(3000, "127.0.0.1");
