import { sleep } from 'k6';
import http from 'k6/http';

// client-basic.js
// 請使用 K6 實作 Basic Mode 壓力測試
// 此模式使用穩定的流量來測試系統的性能，

// 實作需求: 使用 100 個使用者，持續 10 秒鐘

// 實作範例：
// export const options = {
//   vus: 5,          // 代表 5 個使用者同時執行
//   duration: '3s',  // 代表持續 3 秒鐘
// };


export const options = {
  // ===== 請實作以下內容 ======
  vus: 100,
  duration: '10s',
  // ====== 請實作以上內容 ======
};

export default function () {
  http.post('http://localhost:3000/shop');
  sleep(1); // 等待 1 秒鐘，避免過於頻繁的請求
}
