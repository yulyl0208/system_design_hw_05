CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    login TEXT UNIQUE NOT NULL,
    name TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT now()
);

CREATE TABLE exercises (
    id SERIAL PRIMARY KEY,
    name TEXT NOT NULL UNIQUE
);

CREATE TABLE workouts (
    id SERIAL PRIMARY KEY,
    user_id INT NOT NULL REFERENCES users(id) ON DELETE CASCADE,
    created_at TIMESTAMP DEFAULT now()
);

CREATE TABLE workout_exercises (
    workout_id INT REFERENCES workouts(id) ON DELETE CASCADE,
    exercise_id INT REFERENCES exercises(id),
    reps INT NOT NULL CHECK (reps > 0),

    PRIMARY KEY (workout_id, exercise_id)
);

CREATE INDEX idx_workouts_user_id 
ON workouts(user_id);

CREATE INDEX idx_workout_exercises_workout 
ON workout_exercises(workout_id);

CREATE INDEX idx_workout_exercises_exercise 
ON workout_exercises(exercise_id);
