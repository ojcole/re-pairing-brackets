import sys
import os
import subprocess
import time
import shutil

headers = '''
# include <iostream>
# include <list>
# include <set>
# include <string>
# include <utility>
# include <vector>
# include <thread>
# include <algorithm>
# include "generate/generate_all.h"
# include "generate/generate_next.h"
# include "generate/generate_random.h"
# include "generate/generate_random_hard.h"
# include "solve/derived/derived_strategy.h"
# include "solve/greedy/solve_greedy.h"
# include "solve/greedy/solve_simple_greedy.h"
# include "solve/minimise/minimise_width.h"
# include "solve/parallel/solve_parallel.h"
# include "solve/repairings/all_repairings.h"
# include "solve/chistikov/solve_chistikov.h"
# include "stats/random_sample_width.h"
# include "stats/results_output.h"
'''


main_start = "int main() {"
main_end = "}"

script_loc = os.path.dirname(__file__)
workspace_loc = os.path.join(script_loc, "../")

if not os.path.isfile(os.path.join(workspace_loc, "WORKSPACE")):
    print("Error, workspace not found")
    exit()

if len(sys.argv) < 7:
    print(
        "Usage: sample_job.py [from] [to] [samples] [algorithm] [workers] [output_dir]")
    exit()

from_i, to_i, samples, algorithm, workers, output_dir = sys.argv[1:]
equal = False

if workers[0] == '_':
    equal = True
    workers = workers[1:]

algorithm_list = ["RandomUniformSampleWidths", "RandomSymmetricSampleWidths",
                  "RandomHardSampleWidths", "RandomSymmetricHardSampleWidths"]
algorithms = set(algorithm_list)

if not (algorithm in algorithms):
    print("Unknown algorithm " + algorithm)
    print("Expected one of: " + ", ".join(algorithm_list))
    exit()

out_dir = os.path.join(os.getcwd(), output_dir)

if os.path.exists(out_dir):
    print("Output directory path is not empty")
    exit()

os.mkdir(out_dir)

main_file = os.path.join(workspace_loc, "main.cc")

j = 1
for i in range(int(from_i), int(to_i) + 1):
    out_file = open(main_file, "w+")
    out_file.write(headers)
    out_file.write(main_start)
    out_file.write("unsigned int cores =" + workers + ";")
    if not equal:
        out_file.write(
            "cores = std::max(cores, std::thread::hardware_concurrency());")

    out_file.write("auto res = stats::" + algorithm + "(" + samples + ", " + str(i) +
                   ", cores);stats::OutputRandomSampleMinimal(res);std::cout << \"Result for length " + str(i) + ":\" << std::endl; stats::OutputRandomSample(res);")

    out_file.write(main_end)
    out_file.close()
    os.chdir(workspace_loc)

    subprocess.call(["bazel", "build", "main", "--copt=-Ofast", "--copt=-mtune=native", "--copt=-march=native", "--copt=-std=c++2a"],
                    stdout=subprocess.DEVNULL, stderr=subprocess.STDOUT)

    shutil.copy(os.path.join(workspace_loc, "bazel-bin", "main"),
                os.path.join(out_dir, "sample" + str(j)))

    time.sleep(1)

    j = j + 1

rang = int(to_i) - int(from_i) + 1
batch = '''#!/bin/bash
#
#''' + '''
#SBATCH --job-name=sample''' + str(from_i) + "_" + str(to_i) + '''
#SBATCH --partition=cpu-batch
#SBATCH --cpus-per-task=''' + str(workers) + '''
#SBATCH --mem=0
#SBATCH --exclusive
#SBATCH --mail-type=END,FAIL
#SBATCH --output=sample''' + str(from_i) + "_" + str(to_i) + "_%a.out" + '''
#SBATCH --error=sample''' + str(from_i) + "_" + str(to_i) + "_%a.err" + '''
#SBATCH --array=1-''' + str(rang) + '''
#SBATCH --ntasks-per-node=1

CASE="sample"
CASE+=$SLURM_ARRAY_TASK_ID

srun --exclusive --ntasks 1 $CASE
'''

batch_file = open(os.path.join(out_dir, "sample_job.slurm"), "w+")
batch_file.write(batch)
batch_file.close()
