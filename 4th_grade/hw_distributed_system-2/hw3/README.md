1. B
2. A
3. In server: In line 3 and 4, `packageDefinition` is parsed into a js object, then binds to the gRPC networking library.
    ```js
    const packageDefinition = protoLoader.loadSync('owl_post.proto', {});
    const owlPostProto = grpc.loadPackageDefinition(packageDefinition).owlpost;
    ```
    After that, in line 99, the proto is officially registered (Skeleton) to the js code
    ```js
    server.addService(owlPostProto.OwlPost.service, { sendLetter, trackLetter });
    ```
    In client: Initial steps are the same as server, the only difference is a fake server (stub) is created in line 6,
    ```js
    const client = new owlPostProto.OwlPost('localhost:50051', grpc.credentials.createInsecure());
    ```
4. the data type, field number (determine which comes first)
5. In `server.js` line 88:
    ```js
    console.error(`查詢信件狀態 (尾碼 ${pickup_code}): 信件不存在`);

        callback({
            code: grpc.status.NOT_FOUND,
            details: "找不到該信件"
        });
    ```
    print out `查詢信件狀態(尾號 655) 找不到該信件` in `track.js`. Notice that `grpc.status.NOT_FOUND` will cause the word to be red.
6. 咆嘯信已送達
7. Nothing will hapen, say I change `rpc SendLetter (LetterRequest) returns (LetterResponse);` to `rpc send_letter (LetterRequest) returns (LetterResponse);`, all functionalities still work fine. The reason is that grpc parser (const packageDefinition = protoLoader.loadSync('owl_post.proto', {});) will do the syntax translation to match the "native" style of the language one is writing in (JS).