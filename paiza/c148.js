process.stdin.resume();
process.stdin.setEncoding('utf8');
var lines = [];
var reader = require('readline').createInterface({
  input: process.stdin,
  output: process.stdout
});
reader.on('line', (line) => {
  lines.push(line);
});
reader.on('close', () => {
  let [fNum, lv] = lines[0].split(' ').map(Number);
  for(let i = 1; i <= fNum; i++) {
    if (lines[i] < lv) {
      lv += Math.floor(lines[i] / 2)
    } else if (lines[i] > lv) {
      lv = Math.floor(lv / 2)
    }
  }
  console.log(lv);
});