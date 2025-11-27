SELECT p.*, p2.*
FROM  pizzeria p2
CROSS JOIN person p
ORDER BY p.id, p2.id;