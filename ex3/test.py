from gradesCalc import *


def grades_calc_hemi_test():
    # imports for hemi tests
    import os
    import difflib

    # constants
    hemi_path = "/Users/ohadbenacot/CLionProjects/Mtm/ex3/tests/Agressive_tests_Hemi_grades"
    input_basename = "input"
    output_basename = "output"
    my_files_basename = "MY"
    filename_extension = ".txt"
    average_filename = "Averages.txt"
    diff_filename = "diff.txt"
    average_test_str = "Average test{test_num}: {course_avg}\n"
    diff_prompt = "\nDiff Of Input{}\n"

    # Executing Hemi tests into diff files
    os.chdir(hemi_path)
    files = os.listdir()
    inputs = list(filter(lambda x: x.startswith(input_basename), files))
    outputs = list(filter(lambda x: x.startswith(output_basename), files))

    with open(average_filename, 'a') as avg_file:
        avg_file.write("\n\nResults\n------\n")
        for input_file in sorted(inputs):
            input_num = input_file.strip(input_basename).strip(filename_extension)
            my_output_file = "{}{}{}{}".format(my_files_basename, output_basename, input_num, filename_extension)
            course_avg = final_grade(input_path=input_file, output_path=my_output_file)
            avg_file.write(average_test_str.format(test_num=input_num, course_avg=course_avg))

    for output_file in sorted(outputs):
        output_num = output_file.strip(output_basename).strip(filename_extension)
        my_output_file = "{}{}{}{}".format(my_files_basename, output_basename, output_num, filename_extension)
        with open(output_file, 'r') as src_output_file_reader:
            lines = src_output_file_reader.readlines()
        with open(my_output_file, 'r') as source_output_file_reader:
            src_lines = source_output_file_reader.readlines()

        with open(diff_filename, 'a') as diff_file_writer:
            diff_file_writer.write(diff_prompt.format(output_num))
            for line in difflib.unified_diff(lines, src_lines, lineterm=''):
                diff_file_writer.write(line)


# Testing your implemented functions, feel free to add more tests below
def main():
    # Testing the `final_grade` function
    input_path = 'tests/input'
    output_path = 'tests/out'
    course_avg = final_grade(input_path=input_path, output_path=output_path)
    assert course_avg == 70

    # Testing the `check_strings` function
    s1 = 'naanb'
    s2 = 'baNaNa'
    result = check_strings(s1=s1, s2=s2)
    assert result

    grades_calc_hemi_test()


if __name__ == "__main__":
    main()
