#### PART 1 ####
# final_grade: Calculates the final grade for each student, and writes the output (while eliminating illegal
# rows from the input file) into the file in `output_path`. Returns the average of the grades.
#   input_path: Path to the file that contains the input
#   output_path: Path to the file that will contain the output
def final_grade(input_path: str, output_path: str) -> int:
    separator = ','
    sum_valid_grades = 0
    num_valid_students = 0
    student_data_keys = ['name', 'semester', 'homework_avg']

    with open(output_path, 'a') as output_file:
        with open(input_path) as input_file:
            line_str = input_file.readline()
            input_data_values = list(filter(lambda char: char != separator, line_str.split(separator)))
            student_id = int(input_data_values[0])
            student_data_values = input_data_values[1:]
            student_data = dict(zip(student_data_keys, student_data_values))
            if is_valid_student_data(student_data):
                student_final_grade = calculate_final_grade(student_id, student_data)
                student_data_str = "{student_id}, {homework_avg}, {student_final_grade}\n". \
                    format(student_id=student_id,
                           homework_avg=student_data["homework_avg"],
                           student_final_grade=student_final_grade)
                output_file.write(student_data_str)
                sum_valid_grades += student_data["homework_avg"]
                num_valid_students += 1

    if num_valid_students > 0:
        return int(sum_valid_grades / num_valid_students)
    return sum_valid_grades


def is_valid_student_data(student_data: dict) -> bool:
    return all([
        int(student_data.get('id')[0]) != 0,
        student_data.get('name').replace(' ', '').isalpha(),
        int(student_data.get('semester')) >= 1,
        50 < int(student_data.get('homework_avg')) <= 100
    ])


def calculate_final_grade(student_id: int, student_data: dict) -> int:
    return int(int(str(student_id)[-2:]) + int(student_data['homework_avg']) / 2)


#### PART 2 ####
# check_strings: Checks if `s1` can be constructed from `s2`'s characters.
#   s1: The string that we want to check if it can be constructed
#   s2: The string that we want to construct s1 from
def check_strings(s1: str, s2: str) -> bool:
    # TODO: implement here
    raise NotImplementedError
