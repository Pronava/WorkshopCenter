const express = require('express');
const cors = require('cors');
const mysql = require('mysql2');

const app = express();
const PORT = 4000;

app.use(cors());
app.use(express.json());

// 创建 MySQL 连接池（按需调整配置）
const pool = mysql.createPool({
  host: 'localhost',
  port: 3307,        
  user: 'root',
  password: 'root',
  database: 'chat_app',
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0
});


app.get('/api/ping', (req, res) => {
  res.json({ message: '直接从后端获取数据, 前端没有传递参数 aaapong pong pong!' });
});

app.post('/api/count', (req, res) => {
  const { count } = req.body;
  console.log('收到的 count:', count);

  pool.query('SELECT multiplier FROM config LIMIT 1', (err, results) => {
    if (err) {
      console.error('查询乘数出错:', err);
      res.status(500).json({ message: '数据库查询错误' });
      return;
    }

    if (results.length === 0) {
      res.status(400).json({ message: '未找到乘数配置' });
      return;
    }

    const multiplier = results[0].multiplier;
    const result = count * multiplier;

    res.json({ message: `服务器从数据库获取乘数4的计算结果：${count} × ${multiplier} = ${result}` });
  });
});

app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
});
