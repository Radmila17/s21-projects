SELECT
	DISTINCT person_id
FROM
	person_visits pv
WHERE
	pv.pizzeria_id = '2'
	OR (pv.visit_date BETWEEN '2022-01-06' AND '2022-01-09')
ORDER BY
	pv.person_id DESC;