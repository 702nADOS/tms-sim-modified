/**
 * $Id: ald.h 697 2014-09-16 19:43:01Z klugeflo $
 * @file ald.h
 * @brief Abstract List Dispatch scheduler
 * @author Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#ifndef SCHEDULERS_ALD_H
#define SCHEDULERS_ALD_H 1

#include <core/scheduler.h>

#include <list>


namespace tmssim {

  /**
   * @brief Abstract List Dispatch scheduler
   */
  class ALDScheduler : public Scheduler {

  public:
    ALDScheduler();//Logger* _logger = noLogPtr);
    virtual ~ALDScheduler();

    virtual Job* removeJob(Job *job);
    /**
     * @brief Dispatch one job from the schedule for execution
     * This function takes the first element of the ALDScheduler::mySchedule
     * list and executes it for one cycle. If the ALDScheduler::mySchedule
     * list was changed through calls to Scheduler::enqueueJob or
     * Scheduler::schedule, your implementation must ensure to set the
     * ALDScheduler::scheduleChanged variable to true.
     * @param now Point in time, succeeding calls to this functions must have
     * increasing times
     * @param dispatchStat Container for statistics
     * @return finished job, NULL (running/idling), or ESC_DISP error code
     */
    virtual Job* dispatch(int now, DispatchStat& dispatchStat);
    virtual bool hasPendingJobs(void) const;

    virtual void printSchedule() const;

  protected:
    /**
     * @brief Notification about finished Job.
     *
     * This method is called by dispatch() if a job has finished execution.
     * Overwrite it in your scheduler implementation, if you are keeping
     * jobs stored additionally in other data structures. Here, you
     * get a chance to remove references to keep your data structures
     * consistent.
     * @param job the finished job
     */
    virtual void jobFinished(Job *job);


    /**
     * @brief Notification that a job was cancelled.
     *
     * Call this function any time your scheduler implementation decides
     * to cancel a job.
     * @param removedJob the job that was cancelled
     */
    virtual void notifyJobRemoved(const Job *removedJob);


    /**
     * @brief Notification that the schedule changed.
     *
     * Call this function any time your scheduler implementation
     * changes the #mySchedule list.
     */
    virtual void notifyScheduleChanged();


    /**
     * @brief List holding the current schedule.
     *
     * Use this list to store the schedule that is generated by your
     * implementation. Dispatching is performed from the front.
     */
    std::list<Job*> mySchedule;

  private:

    /**
     * @brief The Job that is currently being executed/was executed
     * in the last cycle
     *
     * If you cancel this job in one of your implementations, make sure to
     * update this variable (to NULL).
     */
    Job* currentJob;

    /**
     * @brief Notification that the schedule has changed
     * Set this variable to true any time the ALDScheduler::mySchedule
     * list changed.
     */
    bool scheduleChanged;

  };

} // NS tmssim

#endif /* !SCHEDULERS_ALD_H */
