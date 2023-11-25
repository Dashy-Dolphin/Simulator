The input directory contains the required input loads to the caching algorithms.
The colums are the request sequence, error free predictions for the Mark0 and MarkP algorithm.

The workload in each input file follows the following convention.
<workloadname>_<cache_size_for_predictions>_<max_page_id>_<misses for optimal algorithm>.

The output directory contains the output for the relevant input file and cacheconfiguration.
For <input_name> file,  the output file name will be <input_name>.<cache_replacement_policy_used>.
The first line of the output file will have 
<no_of_unique_requests>,<total_number_of_requests> and <total_number_of_misses>.


All the page id are positive integers.
