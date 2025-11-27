SELECT COALESCE(p.name, '-')AS person_name,
		pv.visit_date AS visit_date,
		COALESCE(piz."name" , '-')	AS pizzeria_name
FROM pizzeria piz
FULL JOIN person_visits pv ON pv.pizzeria_id  = piz.id AND pv.visit_date BETWEEN '2022-01-01' AND '2022-01-03'
FULL JOIN person p ON p.id = pv.person_id AND pv.visit_date BETWEEN '2022-01-01' AND '2022-01-03'
WHERE pv.visit_date BETWEEN '2022-01-01' AND '2022-01-03' OR pv.visit_date IS NULL
ORDER BY person_name , visit_date , pizzeria_name;



SELECT 
    COALESCE(p.name, '-') AS person_name,
	outer_pv.visit_date AS visit_date,
	COALESCE(piz.name, '-') AS pizzeria_name
FROM
	(
	SELECT *
	FROM person_visits pv 
	WHERE pv.visit_date BETWEEN '2022-01-01' AND '2022-01-03'
	) AS outer_pv
FULL JOIN person p ON outer_pv.person_id = p.id
FULL JOIN pizzeria piz ON outer_pv.pizzeria_id = piz.id
ORDER BY person_name, visit_date, pizzeria_name;
