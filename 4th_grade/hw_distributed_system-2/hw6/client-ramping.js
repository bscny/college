import http from 'k6/http';
import { sleep } from 'k6';

// client-ramping.js
// 請使用 K6 實作 Ramping Mode 漸強壓力測試，
// 此模式通常用於測試系統在逐漸增加的負載下的性能，
// 以確保系統能夠穩定地處理增加的請求量。

// 實作需求: 
// 使用 400 個使用者，
// 每 2 秒增加 400 個使用者，
// 直到達到 2400 個使用者，
// 一共持續 12 秒鐘。

// 實作範例：
// export const options = {
//   stages: [
//     { duration: '5s', target: 10 }, // 開始時使用 10 個使用者
//     { duration: '2s', target: 1000 }  // 2 秒後增加到 1000 個使用者
//  ],
// };

export const options = {
  stages: [
    // ===== 請實作以下內容 ======
    { duration: '2s', target: 400 },
    { duration: '2s', target: 800 },
    { duration: '2s', target: 1200 },
    { duration: '2s', target: 1600 },
    { duration: '2s', target: 2000 },
    { duration: '2s', target: 2400 }
    // ====== 請實作以上內容 ======
  ],
};

export default function () {
  http.post('http://localhost:3000/shop');
  sleep(1); // 等待 1 秒鐘，避免過於頻繁的請求
}
