/*First query*/
SELECT missing_date::date
FROM generate_series('2022-01-01', '2022-01-10', INTERVAL '1 day') AS missing_date
LEFT JOIN (SELECT visit_date FROM person_visits pv  WHERE pv.person_id = 1 OR pv.person_id = 2) AS pv ON missing_date = pv.visit_date
WHERE pv.visit_date IS NULL;


/*Second query just for me*/
SELECT dates.missing_date
FROM 
	(SELECT * FROM person_visits pv WHERE pv.person_id = 1 OR pv.person_id = 2) AS pv
RIGHT JOIN 
 	(SELECT generate_series('2022-01-01', '2022-01-10', INTERVAL '1 day')::date AS missing_date) AS dates
ON pv.visit_date = dates.missing_date 
WHERE pv.visit_date IS NULL;