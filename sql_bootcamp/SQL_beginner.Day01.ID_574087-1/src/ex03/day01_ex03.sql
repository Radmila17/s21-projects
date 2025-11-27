SELECT order_date AS action_date, person_id
FROM person_order po
INTERSECT
SELECT visit_date AS action_date, person_id
FROM person_visits pv
ORDER BY action_date ASC, person_id DESC;