// server.js
const express = require('express');
const app = express();
const port = 3000;

let currentVU = 0;
let isSystemStopped = false;
let isSystemStart = false; // 是否已經開始有流量

const MAX_VU = 5000;     // 攻克目標變更為 2000
let MAX_STEP = 600; // 每次流量變化不能超過 100，否則被視為攻擊

let requestLogs = [];

setInterval(() => {
  if (isSystemStart === false ||
    requestLogs.length < MAX_STEP * 0.5
  ) {
    return
  }
  if (
    requestLogs.length - MAX_STEP < 200 || 
    requestLogs.length < MAX_STEP * 3
  ) {
    console.log("⚠️ 偵測到用戶數量變多，提升上限！，當前上限:", MAX_STEP);
    MAX_STEP += 500; // 提升上限，避免誤判
    console.log("新上限:", MAX_STEP);
    console.log("1秒鐘內請求數:", requestLogs.length);
  }
}, 2000); // 每秒執行一次

app.use(express.json());

app.post('/shop', (req, res, next) => {
  isSystemStart = true; // 開始有流量

  try {
    if (isSystemStopped) {
      return res.status(403).send("系統已停止");
    }

    const now = Date.now();
    requestLogs.push(now);
    currentVU++;

    if (currentVU % 250 === 0) {
      console.log(`目前流量 VU 數: ${currentVU}`);
    }
    
    // 移除 1 秒前的請求紀錄
    requestLogs = requestLogs.filter(ts => now - ts <= 1000);

    // 短期內請求數過多 → 視為爆破
    if (requestLogs.length > MAX_STEP) {
      isSystemStopped = true;
      console.warn("💥 爆破偵測觸發，流量變化太快！系統停止！");
      process.exit(1)
      // return res.status(403).send("爆破偵測觸發，系統已關閉！");
    }

    // 成功達到上限
    if (currentVU >= MAX_VU) {
      console.log(`🎉 系統在流量為 ${currentVU} 時被成功攻克! 你成功了`);
      process.exit(1)
      // return res.send(`系統在流量為 ${currentVU} 時被成功攻克! 你成功了`);
    }

    // console.log(`模擬購物成功，目前流量 user 數: ${currentVU}`);
    return res.send(`模擬購物成功，目前流量 user 數: ${currentVU}`);
  } catch (err) {
    next(err);
  }
});

app.use((req, res) => res.status(404).send("找不到資源"));

app.use((err, req, res, next) => {
  console.error("🚨 系統錯誤:", err.stack);
  res.status(500).send("伺服器內部錯誤");
});

app.listen(port, () => {
  console.log(`🛒 購物平台伺服器正在 http://localhost:${port} 上運行...`);
});
