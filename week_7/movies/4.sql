SELECT COUNT(title) FROM movies where id IN (SELECT movie_id FROM ratings WHERE rating == 10.0);
