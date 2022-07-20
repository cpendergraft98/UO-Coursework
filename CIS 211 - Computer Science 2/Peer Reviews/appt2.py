"""
Author: Adriel Azera
Project: appt.py
Credit: Jordan W. and Blake S.
"""

from datetime import datetime


class Appt:
    def __init__(self, start: datetime, finish: datetime, desc: str):
        """An appointment from start time to finish time, with description desc.
        Start and finish should be the same day.
        """
        assert finish > start, f"Period finish ({finish}) must be after start ({start})"
        self.start = start
        self.finish = finish
        self.desc = desc

    def __eq__(self, other: 'Appt') -> bool:
        if self.start == other.start and self.finish == other.finish:
            return True
        else:
            return False

    def __lt__(self, other: 'Appt') -> bool:
        if self.finish <= other.start:
            return True
        else:
            return False

    def __gt__(self, other: 'Appt') -> bool:
        if self.start >= other.finish:
            return True
        else:
            return False

    def overlaps(self, other: 'Appt') -> bool:
        """Is there a non zero overlap between these periods?"""
        if (self.start > other.start and self.finish > other.finish) or \
                (other.start < self.finish and self.start < other.finish)\
                or (self.start < other.start and self.finish > other.finish)\
                or (self.start > other.start and self.finish < other.finish):
            return True
        else:
            return False

    def intersect(self, other: 'Appt') -> 'Appt':
        """The overlapping portion of two Appt objects"""
        assert self.overlaps(other)
        start_list = []
        finish_list = []
        start_list.append(self.start)
        start_list.append(other.start)
        finish_list.append(self.finish)
        finish_list.append(other.finish)
        return Appt(max(start_list), min(finish_list), self.desc + " and " + other.desc)

    def __str__(self) -> str:
        """The textual format of an appointment is
        yyyy-mm-dd hh:mm hh:mm  | description
        Note that this is accurate only if start and finish
        are on the same day.
        """
        date_iso = self.start.date().isoformat()
        start_iso = self.start.time().isoformat(timespec='minutes')
        finish_iso = self.finish.time().isoformat(timespec='minutes')
        return f"{date_iso} {start_iso} {finish_iso} | {self.desc}"

    def __repr__(self) -> str:
        return f"Appt({repr(self.start)}, {repr(self.finish)}, {repr(self.desc)})"


class Agenda:
    """An Agenda is a collection of appointments, similar to a list."""
    def __init__(self):
        self.elements = []
        self.problem = []

    def __eq__(self, other: 'Agenda') -> bool:
        """Delegate to __eq__ (==) of wrapped lists"""
        return self.elements == other

    def __str__(self) -> str:
        """Each Appt on its own line"""
        lines = [str(e) for e in self.elements]
        return "\n".join(lines)

    def append(self, info):
        self.elements.append(info)

    def conflicts(self) -> 'Agenda':
        """Returns an agenda consisting of the conflicts
        (overlaps) between this agenda and the other.
        Side effect: This agenda is sorted
        """
        new_agenda = Agenda()
        self.sort()
        for i in range(len(self.elements)):
            conflict = self.elements[i]
            for q in range(i+1, len(self.elements)):
                conflict2 = self.elements[q]
                if conflict.overlaps(conflict2):
                    new_agenda.append(conflict.intersect(conflict2))
                else:
                    break
        return new_agenda

    def sort(self):
        """Sort agenda by appointment start times"""
        self.elements.sort(key=lambda appt: appt.start)

    def __len__(self) -> int:
        return len(self.elements)


if __name__ == "__main__":
    print("Running usage examples")
    appt1 = Appt(datetime(2018, 3, 15, 13, 30), datetime(2018, 3, 15, 15, 30), "Early afternoon nap")
    appt2 = Appt(datetime(2018, 3, 15, 15, 00), datetime(2018, 3, 15, 16, 00), "Coffee break")
    if appt2 > appt1:
        print(f"appt1 '{appt1}' was over when appt2 '{appt2}'  started")
    elif appt1.overlaps(appt2):
        print("Oh no, a conflict in the schedule!")
        print(appt1.intersect(appt2))
    agenda = Agenda()
    agenda.append(appt1)
    agenda.append(appt2)
    ag_conflicts = agenda.conflicts()
    if len(ag_conflicts) == 0:
        print(f"Agenda has no conflicts")
    else:
        print(f"In agenda:\n{agenda}")
        print(f"Conflicts:\n {ag_conflicts}")

