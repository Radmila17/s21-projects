/*first select with >= <= */
SELECT
	name,
	rating
FROM
	pizzeria p
WHERE
	p.rating >= 3
	AND p.rating <= 5
ORDER BY
	rating;

/*second select with between */
SELECT
	name,
	rating
FROM
	pizzeria p
WHERE
	p.rating BETWEEN 3 AND 5
ORDER BY
	rating;

