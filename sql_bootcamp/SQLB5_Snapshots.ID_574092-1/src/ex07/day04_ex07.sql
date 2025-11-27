INSERT INTO person_visits
SELECT 
	(SELECT max(id) FROM person_visits)+1,
	(SELECT id FROM person WHERE name = 'Dmitriy'),
	(SELECT piz.id 
	FROM pizzeria piz
	JOIN menu m ON m.pizzeria_id = piz.id
	WHERE piz.name NOT IN (SELECT pizzeria_name FROM mv_dmitriy_visits_and_eats)
	AND m.price < 800
	LIMIT 1),
	'2022-01-08';
REFRESH MATERIALIZED VIEW  mv_dmitriy_visits_and_eats;



SELECT * FROM person_visits pv ;
SELECT * FROM pizzeria piz ;
SELECT * FROM  mv_dmitriy_visits_and_eats;