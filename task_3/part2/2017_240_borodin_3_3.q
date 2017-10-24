//This file was generated from (Commercial) UPPAAL 4.0.14 (rev. 5615), May 2014

/*

*/
E<> forall(i:task_id_type) task_is_finished[i] == 1

/*

*/
E<> skip_count <= 16 and forall(i:task_id_type) task_is_finished[i] == 1

/*

*/
E<> skip_count <= 15 and forall(i:task_id_type) task_is_finished[i] == 1

/*

*/
E<> time <= 20 and forall(i:task_id_type) task_is_finished[i] == 1

/*

*/
E<> time <= 21 and forall(i:task_id_type) task_is_finished[i] == 1
