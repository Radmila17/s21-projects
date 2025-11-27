SELECT piz.name AS pizzeria_name
FROM pizzeria piz
JOIN person_visits pv ON piz.id = pv.pizzeria_id AND pv.visit_date = '2022-01-08'
JOIN person p ON p.id = pv.person_id AND p."name" = 'Dmitriy'
JOIN menu m ON m.pizzeria_id = pv.pizzeria_id AND m.price < 800;