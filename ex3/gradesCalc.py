#### PART 1 ####
# final_grade: Calculates the final grade for each student, and writes the output (while eliminating illegal
# rows from the input file) into the file in `output_path`. Returns the average of the grades.
#   input_path: Path to the file that contains the input
#   output_path: Path to the file that will contain the output


def final_grade(input_path: str, output_path: str) -> int:
    separator = ','
    sum_valid_grades = 0
    student_data_keys = ['name', 'semester', 'homework_avg']
    output_data = dict()
    with open(input_path) as input_file:
        lines = input_file.readlines()
    for line in lines:
        input_data_values = list(filter(lambda char: char != separator, line.split(separator)))
        input_data_values = list(map(str.strip, input_data_values))
        student_id = input_data_values[0].strip()
        student_data_values = input_data_values[1:]
        student_data = dict(zip(student_data_keys, student_data_values))
        if is_valid_input(student_id, student_data):
            student_final_grade = calculate_final_grade(student_id, student_data)
            student_str = "{student_id}, {homework_avg}, {student_final_grade}\n". \
                format(student_id=student_id,
                       homework_avg=student_data["homework_avg"],
                       student_final_grade=student_final_grade)
            output_data[student_id] = student_str
            sum_valid_grades += student_final_grade

    with open(output_path, 'w') as output_file:
        output_file.writelines(sorted(output_data.values()))
    if len(output_data) > 0:
        return int(sum_valid_grades / len(output_data))
    return sum_valid_grades


def is_valid_input(student_id: str, student_data: dict) -> bool:
    min_valid_grade = 50
    max_valid_grade = 100
    return all([
        len(str(student_id)) == 8,
        int(str(student_id)[0]) != 0,
        student_data.get('name').replace(' ', '').isalpha(),
        int(student_data.get('semester')) >= 1,
        min_valid_grade < int(student_data.get('homework_avg')) <= max_valid_grade
    ])


def calculate_final_grade(student_id: str, student_data: dict) -> int:
    return int((int(student_id[-2:]) + int(student_data['homework_avg'])) / 2)


#### PART 2 ####
# check_strings: Checks if `s1` can be constructed from `s2`'s characters.
#   s1: The string that we want to check if it can be constructed
#   s2: The string that we want to construct s1 from
def check_strings(s1: str, s2: str) -> bool:
    letters = list(char for char in s2.lower())
    for letter in s1.lower():
        if letter in letters:
            letters.remove(letter)
        else:
            return False
    return True
