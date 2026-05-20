import http from 'k6/http';
import { sleep } from 'k6';

// client-explode.js
// 請使用 K6 實作 Explode Mode 壓力測試，
// 此模式通常用於測試系統在高負載下的性能和穩定性。

// 實作需求: 使用 5000 個使用者，持續 5 秒鐘

export const options = {
  // ===== 請實作以下內容 ======
  vus: 5000,
  duration: '5s',
  // ====== 請實作以上內容 ======
};

export default function () {
  http.post('http://localhost:3000/shop');
  sleep(1); // 等待 1 秒鐘，避免過於頻繁的請求
}
