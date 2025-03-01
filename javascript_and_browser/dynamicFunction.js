function makeValidator(rules) {
  return function validate(data) {
    for (const [key, condition] of Object.entries(rules)) {
      if (!condition(data[key])) {
        throw new Error(`Validation failed for ${key}`);
      }
    }
    return true;
  };
}

const userValidator = makeValidator({
  name: (value) => typeof value === "string" && value.length > 2,
  age: (value) => typeof value === "number" && value > 0,
  email: (value) => /\S+@\S+\.\S+/.test(value)
});

const userData = { name: "Alice", age: 25, email: "alice@example.com" };
console.log(userValidator(userData));

const invalidData = { name: "A", age: -5, email: "invalid" };
console.log(userValidator(invalidData));
