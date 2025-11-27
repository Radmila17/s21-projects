CREATE TABLE cities(point1 VARCHAR, point2 VARCHAR, cost INTEGER);
INSERT INTO cities VALUES ('a', 'b', 10),
			('b', 'a', 10),
			('a', 'd', 20),
			('d', 'a', 20),
			('a', 'c', 15),
			('c', 'a', 15),
			('b', 'd', 25),
			('d', 'b', 25),
			('b', 'c', 35),
			('c', 'b', 35),
			('d', 'c', 30),
			('c', 'd', 30);

WITH RECURSIVE city_count AS 
	(SELECT count (DISTINCT point1) AS c FROM cities),
	 r AS (
	SELECT ARRAY['a'] AS tour,
		0 AS total_cost,
		'a'::varchar AS current_point
    UNION ALL 
    SELECT tour || c.point2,
		total_cost + c.cost,
		c.point2
    FROM r
    JOIN cities c ON c.point1 = current_point 
    WHERE NOT c.point2 = ANY(tour) 
    OR (array_length(tour, 1) = (SELECT c FROM city_count) 
    AND c.point2='a')
    ),
res_table AS
    (SELECT total_cost, tour
     FROM r
     WHERE array_length(tour, 1) = (SELECT c FROM city_count)+1)
SELECT total_cost, CONCAT('{', array_to_string(tour, ','), '}') AS tour
FROM res_table
WHERE total_cost = (SELECT min(total_cost) FROM res_table)
ORDER BY total_cost, tour;


-- Vladimir
WITH RECURSIVE paths AS(
	SELECT point2 AS current_city,
		point2 AS visited_city,
		cost AS total_cost,
		CONCAT('a,', point2) AS path
	FROM cities
	WHERE point1 = 'a' AND point2 != 'a'
	UNION
	SELECT c.point2,
		CONCAT(p.visited_city, ',', c.point2),
		p.total_cost + c.cost,
		CONCAT(p.path, ',', c.point2)
	FROM paths p
	JOIN cities c ON c.point1 = p.current_city
	WHERE (c.point2 = 'a' AND p.visited_city LIKE '%,%,%')
	OR (c.point2 != 'a' AND p.visited_city NOT LIKE CONCAT('%', c.point2, '%'))
	), 
result AS (
	SELECT total_cost,
	CONCAT('{', path, '}') AS tour
	FROM paths
	WHERE current_city = 'a'
)
SELECT total_cost, tour
FROM result
WHERE total_cost = (SELECT MIN(total_cost) FROM result)
ORDER BY total_cost ASC, tour ASC;
