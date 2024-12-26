CREATE TABLE foods(id INT PRIMARY KEY AUTO_INCREMENT, user_id INT, name VARCHAR(31), amount INT);
CREATE TABLE foods_2(id INT PRIMARY KEY AUTO_INCREMENT, user_id INT, name VARCHAR(31), amount INT);

INSERT INTO foods VALUES (DEFAULT, 1, '牛肉', 300), (DEFAULT, 1, '玉ねぎ', 2);
INSERT INTO foods_2 VALUES (DEFAULT, 2, 'にんじん', 1), (DEFAULT, 1, '牛肉', 200);

SELECT name, sum(amount) FROM (
  SELECT name, amount FROM foods WHERE user_id = 1
  UNION ALL
  SELECT name, amount FROM foods_2 WHERE user_id = 1
) AS food GROUP BY name;
