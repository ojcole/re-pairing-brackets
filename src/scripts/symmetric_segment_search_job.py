import sys
import os
import subprocess
import time
import shutil


def generate_code(size, word, worker, workers, cpu_workers, width) -> str:
    headers = '''
#include <iostream>
#include <string>

#include "generate/generate_next_symmetric.h"
#include "helpers/n_choose_k.h"
#include "search/segment_width_search.h"
'''
    first, second = word.split(sep="x")

    main_begin = f'''
int main() {{
  std::string first = "{first}";
  std::string second = "{second}";

  int size = {size};
  int worker = {worker};
  int workers = {workers};

  generate::SymmetricGenerator generator(size);

  auto words = helper::NChooseK(size, size / 2);
  auto group_size = words / workers;

  auto res = (worker - 1) * group_size;

  if (worker == workers) {{
    group_size += words % workers;
  }}

  for (size_t i{{}}; i < res; i++) {{
    generator.GenerateNext();
  }}

  auto result = search::PartialSearchSymmetricSegmentForWidth(first, second, generator,
                                                     {width}, group_size, {cpu_workers});

  std::cout << result.size() << std::endl;

  for (auto w : result) {{
    std::cout << w << std::endl;
  }}
'''

    main_end = '''
  return 0;
}
'''

    return headers + main_begin + main_end


script_loc = os.path.dirname(__file__)
workspace_loc = os.path.join(script_loc, "../")

if not os.path.isfile(os.path.join(workspace_loc, "WORKSPACE")):
    print("Error, workspace not found")
    exit()

if len(sys.argv) < 7:
    print(
        "Usage: segment_search_job.py [word] [size] [width] [cpu-workers] [workers] [output_dir]")
    exit()

word, size, width, cpu_workers, workers, output_dir = sys.argv[1:]

out_dir = os.path.join(os.getcwd(), output_dir)

if os.path.exists(out_dir):
    print("Output directory path is not empty")
    exit()

os.mkdir(out_dir)

manual_file = os.path.join(workspace_loc, "manual", "manual_genned.cc")

for i in range(int(workers)):
    out_file = open(manual_file, "w+")
    out_file.write(generate_code(size, word, i+1, workers, cpu_workers, width))
    out_file.close()
    os.chdir(workspace_loc)

    subprocess.call(["bazel", "build", "//manual:manual_genned", "--copt=-Ofast", "--copt=-mtune=native", "--copt=-march=native", "--copt=-std=c++2a"],
                    stdout=subprocess.DEVNULL, stderr=subprocess.STDOUT)

    shutil.copy(os.path.join(workspace_loc, "bazel-bin", "manual", "manual_genned"),
                os.path.join(out_dir, "worker" + str(i+1)))

    time.sleep(1)

batch = f'''#!/bin/bash
#
#
#SBATCH --job-name=segsearch{size}
#SBATCH --partition=cpu-batch
#SBATCH --cpus-per-task={cpu_workers}
#SBATCH --mem=0
#SBATCH --exclusive
#SBATCH --mail-type=END,FAIL
#SBATCH --output=segsearch{size}_worker%a.out
#SBATCH --error=segsearch{size}_worker%a.err
#SBATCH --array=1-{workers}
#SBATCH --ntasks-per-node=1

CASE="worker"
CASE+=$SLURM_ARRAY_TASK_ID

srun --exclusive --ntasks 1 --hint=compute_bound $CASE
'''

batch_file = open(os.path.join(out_dir, "seg_search.slurm"), "w+")
batch_file.write(batch)
batch_file.close()
