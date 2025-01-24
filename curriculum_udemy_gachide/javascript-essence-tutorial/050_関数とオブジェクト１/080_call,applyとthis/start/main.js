function a() {
  console.log("hello " + this.name);
}

const b = a.bind({ name: "Tim" });

b();
