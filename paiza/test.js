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
  const [seatsCount, groupsCount] = lines[0].split(' ').map(Number);
  const occupiedSeats = new Array(seatsCount);
  let sitting = 0;

  for(let i = 1; i <= groupsCount; i++) {
    const [size, first] = lines[i].split(' ').map(Number);

    let flg = true
    for(let y = first - 1; y < first - 1 + size; y++) {
      if (occupiedSeats[y]) {
        flg = false;
        break;
      }
    }
    if (flg) {
      occupiedSeats.fill(true, first - 1, first + size - 1)
      sitting += size;
    }

  }

  console.log(sitting);
});