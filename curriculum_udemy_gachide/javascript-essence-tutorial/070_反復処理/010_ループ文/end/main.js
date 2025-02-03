const a = function () {
	console.log('hello')
}

for(
	let i = 0;
	i < 10;
	a() && i++
) {
	console.log(i);
}

// let i = 0;
// while(i < 10) {
// 	console.log(i);
// 	i++;
// }