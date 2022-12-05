const express = require('express');
const app = express();
const path = require('path');
let result = 'g';
//Ports
const PORT = 5500;
const hostname = '127.0.0.1:';

app.use(
    express.urlencoded({
        extended: true,
    }),
)
app.use(express.json())

const cors = require("cors");
app.use(
	cors({
		// accept vercel
		// origin: "https://projeto3-client.vercel.app/",

		// accept any request from any origin
		origin: "*",
	})
);
app.use(express.static("./front"));

app.get("/", (req, res) => {
    res.sendFile(path.join(__dirname, "../front/index.html"));
  });

app.get('/var', (req, res) => {
    res.send({result});
})
app.post('/var',(req,res) => {
    const { resp } = req.body;
    result = resp;
    res.status(200).json({
        message: "Ok!"
    })
})

app.listen(PORT,() => {
    console.log(`Page server running at http://${hostname}${PORT}/`);
  });
  